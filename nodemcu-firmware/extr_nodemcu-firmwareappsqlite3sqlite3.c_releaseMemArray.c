#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pnBytesFreed; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_9__ {scalar_t__ db; int flags; scalar_t__ szMalloc; int /*<<< orphan*/  zMalloc; } ;
typedef  TYPE_2__ Mem ;

/* Variables and functions */
 int MEM_Agg ; 
 int MEM_Dyn ; 
 int MEM_Frame ; 
 int MEM_RowSet ; 
 int MEM_Undefined ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFreeNN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCheckMemInvariants (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void releaseMemArray(Mem *p, int N){
  if( p && N ){
    Mem *pEnd = &p[N];
    sqlite3 *db = p->db;
    if( db->pnBytesFreed ){
      do{
        if( p->szMalloc ) sqlite3DbFree(db, p->zMalloc);
      }while( (++p)<pEnd );
      return;
    }
    do{
      assert( (&p[1])==pEnd || p[0].db==p[1].db );
      assert( sqlite3VdbeCheckMemInvariants(p) );

      /* This block is really an inlined version of sqlite3VdbeMemRelease()
      ** that takes advantage of the fact that the memory cell value is
      ** being set to NULL after releasing any dynamic resources.
      **
      ** The justification for duplicating code is that according to
      ** callgrind, this causes a certain test case to hit the CPU 4.7
      ** percent less (x86 linux, gcc version 4.1.2, -O6) than if
      ** sqlite3MemRelease() were called from here. With -O2, this jumps
      ** to 6.6 percent. The test case is inserting 1000 rows into a table
      ** with no indexes using a single prepared INSERT statement, bind()
      ** and reset(). Inserts are grouped into a transaction.
      */
      testcase( p->flags & MEM_Agg );
      testcase( p->flags & MEM_Dyn );
      testcase( p->flags & MEM_Frame );
      testcase( p->flags & MEM_RowSet );
      if( p->flags&(MEM_Agg|MEM_Dyn|MEM_Frame|MEM_RowSet) ){
        sqlite3VdbeMemRelease(p);
      }else if( p->szMalloc ){
        sqlite3DbFreeNN(db, p->zMalloc);
        p->szMalloc = 0;
      }

      p->flags = MEM_Undefined;
    }while( (++p)<pEnd );
  }
}