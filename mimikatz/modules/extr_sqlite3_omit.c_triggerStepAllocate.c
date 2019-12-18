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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_10__ {char* zTarget; int /*<<< orphan*/  zSpan; int /*<<< orphan*/  op; } ;
typedef  TYPE_1__ TriggerStep ;
struct TYPE_11__ {scalar_t__ n; int /*<<< orphan*/  z; } ;
typedef  TYPE_2__ Token ;
struct TYPE_12__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 scalar_t__ IN_RENAME_OBJECT ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* sqlite3DbMallocZero (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3Dequote (char*) ; 
 int /*<<< orphan*/  sqlite3RenameTokenMap (TYPE_3__*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  triggerSpanDup (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static TriggerStep *triggerStepAllocate(
  Parse *pParse,              /* Parser context */
  u8 op,                      /* Trigger opcode */
  Token *pName,               /* The target name */
  const char *zStart,         /* Start of SQL text */
  const char *zEnd            /* End of SQL text */
){
  sqlite3 *db = pParse->db;
  TriggerStep *pTriggerStep;

  pTriggerStep = sqlite3DbMallocZero(db, sizeof(TriggerStep) + pName->n + 1);
  if( pTriggerStep ){
    char *z = (char*)&pTriggerStep[1];
    memcpy(z, pName->z, pName->n);
    sqlite3Dequote(z);
    pTriggerStep->zTarget = z;
    pTriggerStep->op = op;
    pTriggerStep->zSpan = triggerSpanDup(db, zStart, zEnd);
    if( IN_RENAME_OBJECT ){
      sqlite3RenameTokenMap(pParse, pTriggerStep->zTarget, pName);
    }
  }
  return pTriggerStep;
}