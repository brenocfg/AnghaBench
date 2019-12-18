#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int volatile u32 ;
typedef  int ht_slot ;
typedef  int /*<<< orphan*/  Wal ;

/* Variables and functions */
 int HASHTABLE_NSLOT ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  walCleanupHash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walFramePage (int volatile) ; 
 int walHash (int volatile) ; 
 int walHashGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int volatile**,int volatile**,int volatile*) ; 
 int walNextHash (int) ; 

__attribute__((used)) static int walIndexAppend(Wal *pWal, u32 iFrame, u32 iPage){
  int rc;                         /* Return code */
  u32 iZero = 0;                  /* One less than frame number of aPgno[1] */
  volatile u32 *aPgno = 0;        /* Page number array */
  volatile ht_slot *aHash = 0;    /* Hash table */

  rc = walHashGet(pWal, walFramePage(iFrame), &aHash, &aPgno, &iZero);

  /* Assuming the wal-index file was successfully mapped, populate the
  ** page number array and hash table entry.
  */
  if( rc==SQLITE_OK ){
    int iKey;                     /* Hash table key */
    int idx;                      /* Value to write to hash-table slot */
    int nCollide;                 /* Number of hash collisions */

    idx = iFrame - iZero;
    assert( idx <= HASHTABLE_NSLOT/2 + 1 );

    /* If this is the first entry to be added to this hash-table, zero the
    ** entire hash table and aPgno[] array before proceeding.
    */
    if( idx==1 ){
      int nByte = (int)((u8 *)&aHash[HASHTABLE_NSLOT] - (u8 *)&aPgno[1]);
      memset((void*)&aPgno[1], 0, nByte);
    }

    /* If the entry in aPgno[] is already set, then the previous writer
    ** must have exited unexpectedly in the middle of a transaction (after
    ** writing one or more dirty pages to the WAL to free up memory).
    ** Remove the remnants of that writers uncommitted transaction from
    ** the hash-table before writing any new entries.
    */
    if( aPgno[idx] ){
      walCleanupHash(pWal);
      assert( !aPgno[idx] );
    }

    /* Write the aPgno[] array entry and the hash-table slot. */
    nCollide = idx;
    for(iKey=walHash(iPage); aHash[iKey]; iKey=walNextHash(iKey)){
      if( (nCollide--)==0 ) return SQLITE_CORRUPT_BKPT;
    }
    aPgno[idx] = iPage;
    aHash[iKey] = (ht_slot)idx;

#ifdef SQLITE_ENABLE_EXPENSIVE_ASSERT
    /* Verify that the number of entries in the hash table exactly equals
    ** the number of entries in the mapping region.
    */
    {
      int i;           /* Loop counter */
      int nEntry = 0;  /* Number of entries in the hash table */
      for(i=0; i<HASHTABLE_NSLOT; i++){ if( aHash[i] ) nEntry++; }
      assert( nEntry==idx );
    }

    /* Verify that the every entry in the mapping region is reachable
    ** via the hash table.  This turns out to be a really, really expensive
    ** thing to check, so only do this occasionally - not on every
    ** iteration.
    */
    if( (idx&0x3ff)==0 ){
      int i;           /* Loop counter */
      for(i=1; i<=idx; i++){
        for(iKey=walHash(aPgno[i]); aHash[iKey]; iKey=walNextHash(iKey)){
          if( aHash[iKey]==i ) break;
        }
        assert( aHash[iKey]==i );
      }
    }
#endif /* SQLITE_ENABLE_EXPENSIVE_ASSERT */
  }


  return rc;
}