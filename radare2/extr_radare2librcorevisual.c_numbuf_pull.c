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
 int atoi (scalar_t__*) ; 
 scalar_t__* numbuf ; 
 int numbuf_i ; 

__attribute__((used)) static int numbuf_pull() {
	int distance = 1;
	if (numbuf_i) {
		numbuf[numbuf_i] = 0;
		distance = atoi (numbuf);
		if (!distance) {
			distance = 1;
		}
		numbuf_i = 0;
	}
	return distance;
}