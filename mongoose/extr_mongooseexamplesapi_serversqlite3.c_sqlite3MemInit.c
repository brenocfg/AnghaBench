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

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (void*) ; 

__attribute__((used)) static int sqlite3MemInit(void *NotUsed){
#if defined(__APPLE__) && !defined(SQLITE_WITHOUT_ZONEMALLOC)
  int cpuCount;
  size_t len;
  if( _sqliteZone_ ){
    return SQLITE_OK;
  }
  len = sizeof(cpuCount);
  /* One usually wants to use hw.acctivecpu for MT decisions, but not here */
  sysctlbyname("hw.ncpu", &cpuCount, &len, NULL, 0);
  if( cpuCount>1 ){
    /* defer MT decisions to system malloc */
    _sqliteZone_ = malloc_default_zone();
  }else{
    /* only 1 core, use our own zone to contention over global locks, 
    ** e.g. we have our own dedicated locks */
    bool success;
    malloc_zone_t* newzone = malloc_create_zone(4096, 0);
    malloc_set_zone_name(newzone, "Sqlite_Heap");
    do{
      success = OSAtomicCompareAndSwapPtrBarrier(NULL, newzone, 
                                 (void * volatile *)&_sqliteZone_);
    }while(!_sqliteZone_);
    if( !success ){
      /* somebody registered a zone first */
      malloc_destroy_zone(newzone);
    }
  }
#endif
  UNUSED_PARAMETER(NotUsed);
  return SQLITE_OK;
}