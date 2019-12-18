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
typedef  int /*<<< orphan*/  ut64 ;
typedef  int /*<<< orphan*/  ut32 ;
struct TYPE_4__ {int /*<<< orphan*/  anal; } ;
struct TYPE_5__ {TYPE_1__ analb; } ;
typedef  TYPE_2__ RParse ;
typedef  int /*<<< orphan*/  RAnalFunction ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* get_fcn_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_num_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static bool varsub(RParse *p, RAnalFunction *f, ut64 addr, int oplen, char *data, char *str, int len) {
	char *fcn_name = NULL;
	str[0] = 0;
	if (!strncmp (data, "call ", 5)) {
		ut32 fcn_id = (ut32) r_num_get (NULL, data + 5);
		if (!(fcn_name = get_fcn_name (p->analb.anal, fcn_id))) {
			return false;
		}
		snprintf (str, len, "call sym.%s", fcn_name);
		free (fcn_name);
		return true;
	}
	return false;
}