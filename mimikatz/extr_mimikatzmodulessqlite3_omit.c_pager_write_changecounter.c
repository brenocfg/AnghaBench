#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_5__ {scalar_t__ pData; TYPE_1__* pPager; } ;
struct TYPE_4__ {scalar_t__ dbFileVers; } ;
typedef  TYPE_2__ PgHdr ;

/* Variables and functions */
 scalar_t__ SQLITE_VERSION_NUMBER ; 
 int /*<<< orphan*/  put32bits (char*,scalar_t__) ; 
 scalar_t__ sqlite3Get4byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pager_write_changecounter(PgHdr *pPg){
  u32 change_counter;

  /* Increment the value just read and write it back to byte 24. */
  change_counter = sqlite3Get4byte((u8*)pPg->pPager->dbFileVers)+1;
  put32bits(((char*)pPg->pData)+24, change_counter);

  /* Also store the SQLite version number in bytes 96..99 and in
  ** bytes 92..95 store the change counter for which the version number
  ** is valid. */
  put32bits(((char*)pPg->pData)+92, change_counter);
  put32bits(((char*)pPg->pData)+96, SQLITE_VERSION_NUMBER);
}