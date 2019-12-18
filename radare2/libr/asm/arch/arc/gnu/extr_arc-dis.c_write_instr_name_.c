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
struct arcDisState {int nullifyMode; int /*<<< orphan*/  instrBuffer; } ;

/* Variables and functions */
#define  BR_exec_always 130 
#define  BR_exec_when_jump 129 
#define  BR_exec_when_no_jump 128 
 char** condName ; 
 char* cond_code_name (struct arcDisState*,int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
write_instr_name_(struct arcDisState * state,
		  const char * instrName,
		  int cond,
		  int condCodeIsPartOfName,
		  int flag,
		  int signExtend,
		  int addrWriteBack,
		  int directMem)
{
  strncpy (state->instrBuffer, instrName, sizeof (state->instrBuffer)-1);
  if (cond > 0)
    {
      const char *cc = 0;

      if (!condCodeIsPartOfName) {
	      strcat (state->instrBuffer, ".");
      }
      if (cond < 16) {
	      cc = condName[cond];
      } else {
	      cc = cond_code_name (state, cond);
      }
      if (!cc) {
	      cc = "???";
      }
      strcat (state->instrBuffer, cc);
    }
    if (flag) {
	    strcat (state->instrBuffer, ".f");
    }
    switch (state->nullifyMode) {
    case BR_exec_always:
      strcat (state->instrBuffer, ".d");
      break;
    case BR_exec_when_jump:
      strcat (state->instrBuffer, ".jd");
      break;
    case BR_exec_when_no_jump:
      break;
    }
    if (signExtend) {
	    strcat (state->instrBuffer, ".x");
    }
    if (addrWriteBack) {
	    strcat (state->instrBuffer, ".a");
    }
    if (directMem) {
	    strcat (state->instrBuffer, ".di");
    }
}