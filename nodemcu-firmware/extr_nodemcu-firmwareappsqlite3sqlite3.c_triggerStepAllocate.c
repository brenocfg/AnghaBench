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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_6__ {char* zTarget; int /*<<< orphan*/  op; } ;
typedef  TYPE_1__ TriggerStep ;
struct TYPE_7__ {scalar_t__ n; int /*<<< orphan*/  z; } ;
typedef  TYPE_2__ Token ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* sqlite3DbMallocZero (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3Dequote (char*) ; 

__attribute__((used)) static TriggerStep *triggerStepAllocate(
  sqlite3 *db,                /* Database connection */
  u8 op,                      /* Trigger opcode */
  Token *pName                /* The target name */
){
  TriggerStep *pTriggerStep;

  pTriggerStep = sqlite3DbMallocZero(db, sizeof(TriggerStep) + pName->n + 1);
  if( pTriggerStep ){
    char *z = (char*)&pTriggerStep[1];
    memcpy(z, pName->z, pName->n);
    sqlite3Dequote(z);
    pTriggerStep->zTarget = z;
    pTriggerStep->op = op;
  }
  return pTriggerStep;
}