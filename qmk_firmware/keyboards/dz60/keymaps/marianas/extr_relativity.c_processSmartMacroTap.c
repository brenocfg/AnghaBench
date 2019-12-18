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
typedef  int uint16_t ;

/* Variables and functions */
#define  KC_C 137 
#define  KC_D 136 
#define  KC_G 135 
#define  KC_I 134 
#define  KC_N 133 
#define  KC_P 132 
#define  KC_Q 131 
#define  KC_S 130 
#define  KC_T 129 
#define  KC_W 128 
 int /*<<< orphan*/  ReplaceString (char*,char*) ; 
 scalar_t__ TIMER_DIFF_16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  addKeyCode (int) ; 
 int /*<<< orphan*/  containsCode (int const) ; 
 int /*<<< orphan*/  deactivateRelativity () ; 
 int /*<<< orphan*/  last2CodeAre (int const) ; 
 int /*<<< orphan*/  last2CodesAre (int const,int const) ; 
 int /*<<< orphan*/  lastCodeIs (int const) ; 
 int /*<<< orphan*/  printString (char*) ; 
 int /*<<< orphan*/  printStringAndQueueChar (char*) ; 
 scalar_t__ relTimeout ; 
 scalar_t__ relativityTimer ; 
 int /*<<< orphan*/  timer_read () ; 

bool processSmartMacroTap(uint16_t kc)
{
  if (relativityTimer > 0 && TIMER_DIFF_16(timer_read(), relativityTimer) >= relTimeout)
  {
    deactivateRelativity();
    return true;
  }
  relativityTimer = 0;
  switch(kc)
  {
    case KC_C:
      if (containsCode(KC_D))
      {
        printString("ribution");
        printStringAndQueueChar("Center");
      }
      else if (last2CodeAre(KC_C))
      {
        ReplaceString("Corporation", "Contact");
      }
      else if(lastCodeIs(KC_C))
      {
        printString("oration");
      }
      else
      {
        printStringAndQueueChar("Corp");
      }
      break;
    case KC_D:
      if (last2CodeAre(KC_D))
      {
        ReplaceString("Distribution", "Distributor");
      }
      else if(lastCodeIs(KC_D))
      {
        printString("ribution");
      }
      else
      {
        printStringAndQueueChar("Dist");
      }
      break;
    case KC_G:
        printStringAndQueueChar("Global");
        printStringAndQueueChar("Lookup");
      break;
    case KC_I:
      if (containsCode(KC_W))
        printStringAndQueueChar("Instance");
      else
        printStringAndQueueChar("Item");
      break;
    case KC_N:
      printStringAndQueueChar("NadRate");
      break;
    case KC_P:
      if (last2CodesAre(KC_D, KC_C))
      {
        ReplaceString("DistributionCenter", "DistCenter");
        printStringAndQueueChar("Pricing");
      }
      else if (last2CodeAre(KC_P))
      {
      }
      else if(lastCodeIs(KC_P))
      {
        ReplaceString("Product", "Person");
      }
      else
      {
        printStringAndQueueChar("Product");
      }
      break;
    case KC_Q:
      printStringAndQueueChar("Darden");
      break;
    case KC_S:
      if (containsCode(KC_W))
        if (containsCode(KC_S) || containsCode(KC_D))
          printStringAndQueueChar("Step");
        else
          printStringAndQueueChar("Session");
      else
        printStringAndQueueChar("Supplier");
      break;
    case KC_T:
      if (containsCode(KC_W))
        printStringAndQueueChar("Task");
      else
        printStringAndQueueChar("Type");
      break;
    case KC_W:
      printStringAndQueueChar("Workflow");
      break;
  }
  addKeyCode(kc);
  return false;
}