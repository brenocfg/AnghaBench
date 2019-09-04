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

/* Variables and functions */
 char* PG (int /*<<< orphan*/ ) ; 
 char* SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_charset ; 
 int /*<<< orphan*/  internal_encoding ; 

__attribute__((used)) static char *get_default_charset(void) {
	if (PG(internal_encoding) && PG(internal_encoding)[0]) {
		return PG(internal_encoding);
	} else if (SG(default_charset) && SG(default_charset)[0] ) {
		return SG(default_charset);
	}
	return NULL;
}