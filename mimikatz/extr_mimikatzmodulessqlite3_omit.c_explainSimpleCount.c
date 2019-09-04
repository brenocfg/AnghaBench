#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  zName; } ;
typedef  TYPE_1__ Table ;
struct TYPE_12__ {char* zName; } ;
struct TYPE_11__ {int explain; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ Index ;

/* Variables and functions */
 scalar_t__ HasRowid (TYPE_1__*) ; 
 int /*<<< orphan*/  IsPrimaryKeyIndex (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3VdbeExplain (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void explainSimpleCount(
  Parse *pParse,                  /* Parse context */
  Table *pTab,                    /* Table being queried */
  Index *pIdx                     /* Index used to optimize scan, or NULL */
){
  if( pParse->explain==2 ){
    int bCover = (pIdx!=0 && (HasRowid(pTab) || !IsPrimaryKeyIndex(pIdx)));
    sqlite3VdbeExplain(pParse, 0, "SCAN TABLE %s%s%s",
        pTab->zName,
        bCover ? " USING COVERING INDEX " : "",
        bCover ? pIdx->zName : ""
    );
  }
}