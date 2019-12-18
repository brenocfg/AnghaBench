#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct _ht {int dummy; } ;
struct TYPE_7__ {unsigned int htsize; TYPE_1__* first; struct _ht* ht; } ;
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  nKey; int /*<<< orphan*/  pKey; } ;
typedef  TYPE_1__ HashElem ;
typedef  TYPE_2__ Hash ;

/* Variables and functions */
 unsigned int SQLITE_MALLOC_SOFT_LIMIT ; 
 int /*<<< orphan*/  insertElement (TYPE_2__*,struct _ht*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct _ht*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 scalar_t__ sqlite3Malloc (unsigned int) ; 
 int sqlite3MallocSize (struct _ht*) ; 
 int /*<<< orphan*/  sqlite3_free (struct _ht*) ; 
 unsigned int strHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rehash(Hash *pH, unsigned int new_size){
  struct _ht *new_ht;            /* The new hash table */
  HashElem *elem, *next_elem;    /* For looping over existing elements */

#if SQLITE_MALLOC_SOFT_LIMIT>0
  if( new_size*sizeof(struct _ht)>SQLITE_MALLOC_SOFT_LIMIT ){
    new_size = SQLITE_MALLOC_SOFT_LIMIT/sizeof(struct _ht);
  }
  if( new_size==pH->htsize ) return 0;
#endif

  /* The inability to allocates space for a larger hash table is
  ** a performance hit but it is not a fatal error.  So mark the
  ** allocation as a benign. Use sqlite3Malloc()/memset(0) instead of 
  ** sqlite3MallocZero() to make the allocation, as sqlite3MallocZero()
  ** only zeroes the requested number of bytes whereas this module will
  ** use the actual amount of space allocated for the hash table (which
  ** may be larger than the requested amount).
  */
  sqlite3BeginBenignMalloc();
  new_ht = (struct _ht *)sqlite3Malloc( new_size*sizeof(struct _ht) );
  sqlite3EndBenignMalloc();

  if( new_ht==0 ) return 0;
  sqlite3_free(pH->ht);
  pH->ht = new_ht;
  pH->htsize = new_size = sqlite3MallocSize(new_ht)/sizeof(struct _ht);
  memset(new_ht, 0, new_size*sizeof(struct _ht));
  for(elem=pH->first, pH->first=0; elem; elem = next_elem){
    unsigned int h = strHash(elem->pKey, elem->nKey) % new_size;
    next_elem = elem->next;
    insertElement(pH, &new_ht[h], elem);
  }
  return 1;
}