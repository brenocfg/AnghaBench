#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* aLimit; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 size_t SQLITE_LIMIT_ATTACHED ; 
 size_t SQLITE_LIMIT_COLUMN ; 
 size_t SQLITE_LIMIT_COMPOUND_SELECT ; 
 size_t SQLITE_LIMIT_EXPR_DEPTH ; 
 size_t SQLITE_LIMIT_FUNCTION_ARG ; 
 size_t SQLITE_LIMIT_LENGTH ; 
 size_t SQLITE_LIMIT_LIKE_PATTERN_LENGTH ; 
 size_t SQLITE_LIMIT_SQL_LENGTH ; 
 size_t SQLITE_LIMIT_TRIGGER_DEPTH ; 
 size_t SQLITE_LIMIT_VARIABLE_NUMBER ; 
 size_t SQLITE_LIMIT_VDBE_OP ; 
 size_t SQLITE_LIMIT_WORKER_THREADS ; 
 int SQLITE_MAX_ATTACHED ; 
 int SQLITE_MAX_COLUMN ; 
 int SQLITE_MAX_COMPOUND_SELECT ; 
 int SQLITE_MAX_EXPR_DEPTH ; 
 int SQLITE_MAX_FUNCTION_ARG ; 
 int SQLITE_MAX_LENGTH ; 
 int SQLITE_MAX_LIKE_PATTERN_LENGTH ; 
 int SQLITE_MAX_SQL_LENGTH ; 
 int SQLITE_MAX_TRIGGER_DEPTH ; 
 int SQLITE_MAX_VARIABLE_NUMBER ; 
 int SQLITE_MAX_VDBE_OP ; 
 int SQLITE_MAX_WORKER_THREADS ; 
 int /*<<< orphan*/  SQLITE_MISUSE_BKPT ; 
 int SQLITE_N_LIMIT ; 
 int* aHardLimit ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3SafetyCheckOk (TYPE_1__*) ; 

int sqlite3_limit(sqlite3 *db, int limitId, int newLimit){
  int oldLimit;

#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(db) ){
    (void)SQLITE_MISUSE_BKPT;
    return -1;
  }
#endif

  /* EVIDENCE-OF: R-30189-54097 For each limit category SQLITE_LIMIT_NAME
  ** there is a hard upper bound set at compile-time by a C preprocessor
  ** macro called SQLITE_MAX_NAME. (The "_LIMIT_" in the name is changed to
  ** "_MAX_".)
  */
  assert( aHardLimit[SQLITE_LIMIT_LENGTH]==SQLITE_MAX_LENGTH );
  assert( aHardLimit[SQLITE_LIMIT_SQL_LENGTH]==SQLITE_MAX_SQL_LENGTH );
  assert( aHardLimit[SQLITE_LIMIT_COLUMN]==SQLITE_MAX_COLUMN );
  assert( aHardLimit[SQLITE_LIMIT_EXPR_DEPTH]==SQLITE_MAX_EXPR_DEPTH );
  assert( aHardLimit[SQLITE_LIMIT_COMPOUND_SELECT]==SQLITE_MAX_COMPOUND_SELECT);
  assert( aHardLimit[SQLITE_LIMIT_VDBE_OP]==SQLITE_MAX_VDBE_OP );
  assert( aHardLimit[SQLITE_LIMIT_FUNCTION_ARG]==SQLITE_MAX_FUNCTION_ARG );
  assert( aHardLimit[SQLITE_LIMIT_ATTACHED]==SQLITE_MAX_ATTACHED );
  assert( aHardLimit[SQLITE_LIMIT_LIKE_PATTERN_LENGTH]==
                                               SQLITE_MAX_LIKE_PATTERN_LENGTH );
  assert( aHardLimit[SQLITE_LIMIT_VARIABLE_NUMBER]==SQLITE_MAX_VARIABLE_NUMBER);
  assert( aHardLimit[SQLITE_LIMIT_TRIGGER_DEPTH]==SQLITE_MAX_TRIGGER_DEPTH );
  assert( aHardLimit[SQLITE_LIMIT_WORKER_THREADS]==SQLITE_MAX_WORKER_THREADS );
  assert( SQLITE_LIMIT_WORKER_THREADS==(SQLITE_N_LIMIT-1) );


  if( limitId<0 || limitId>=SQLITE_N_LIMIT ){
    return -1;
  }
  oldLimit = db->aLimit[limitId];
  if( newLimit>=0 ){                   /* IMP: R-52476-28732 */
    if( newLimit>aHardLimit[limitId] ){
      newLimit = aHardLimit[limitId];  /* IMP: R-51463-25634 */
    }
    db->aLimit[limitId] = newLimit;
  }
  return oldLimit;                     /* IMP: R-53341-35419 */
}