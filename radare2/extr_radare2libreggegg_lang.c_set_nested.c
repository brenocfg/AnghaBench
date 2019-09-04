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
struct TYPE_4__ {int /*<<< orphan*/ * nested; } ;
struct TYPE_5__ {TYPE_1__ lang; } ;
typedef  TYPE_2__ REgg ;

/* Variables and functions */
 int CTX ; 
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static void set_nested(REgg *egg, const char *s) {
	int i = 0;
	if (CTX < 1) {
		return;
	}
	free (egg->lang.nested[CTX]);
	egg->lang.nested[CTX] = strdup (s);
	// egg->lang.nestedi[c]++;
	// seems not need to increase egg->lang.nestedi[c]
	/** clear inner levels **/
	for (i = 1; i < 10; i++) {
		// egg->lang.nestedi[context+i] = 0;
		R_FREE (egg->lang.nested[CTX + i]);
	}
}