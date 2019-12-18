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
typedef  int /*<<< orphan*/  uint16_t ;
struct csum_state {int /*<<< orphan*/  sum; } ;

/* Variables and functions */
 int /*<<< orphan*/  csum_update (char*,int,struct csum_state*) ; 

uint16_t
csum_get(struct csum_state *css)
{
	char pad = 0;

	csum_update(&pad, 1, css);
	return css->sum;
}