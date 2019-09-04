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
struct arcDisState {int /*<<< orphan*/  instrBuffer; scalar_t__ nullifyMode; } ;

/* Variables and functions */
 char** condName ; 
 char* cond_code_name (struct arcDisState*,int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
write_instr_name_(struct arcDisState *state,
		  const char *instrName,
		  int cond,
		  int condCodeIsPartOfName,
		  int flag,
		  int signExtend,
		  int addrWriteBack,
		  int directMem)
{
	if (!instrName) {
		return;
	}
	strncpy (state->instrBuffer, instrName, sizeof (state->instrBuffer) - 1);
	if (cond > 0) {
		int condlim = 0; /* condition code limit*/
		const char *cc = 0;
		if (!condCodeIsPartOfName) {
			strcat (state->instrBuffer, ".");
		}
		condlim = 18;
		if (cond < condlim) {
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
    if (state->nullifyMode) {
	    if (strstr (state->instrBuffer, ".d") == NULL) {
		    strcat (state->instrBuffer, ".d");
	    }
    }
    if (signExtend) {
	    strcat (state->instrBuffer, ".x");
    }
    switch (addrWriteBack) {
    case 1: strcat(state->instrBuffer, ".a"); break;
    case 2: strcat(state->instrBuffer, ".ab"); break;
    case 3: strcat(state->instrBuffer, ".as"); break;
  }
  if (directMem) {
	  strcat (state->instrBuffer, ".di");
  }
}