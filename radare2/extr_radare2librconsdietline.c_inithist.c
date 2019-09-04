#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; char** data; } ;
struct TYPE_4__ {TYPE_1__ history; } ;

/* Variables and functions */
 TYPE_2__ I ; 
 int R_LINE_HISTSIZE ; 
 int /*<<< orphan*/  ZERO_FILL (TYPE_1__) ; 
 scalar_t__ calloc (int,int) ; 

__attribute__((used)) static int inithist() {
	ZERO_FILL (I.history);
	if ((I.history.size + 1024) * sizeof (char *) < I.history.size) {
		return false;
	}
	I.history.data = (char **) calloc ((I.history.size + 1024), sizeof(char *));
	if (!I.history.data) {
		return false;
	}
	I.history.size = R_LINE_HISTSIZE;
	return true;
}