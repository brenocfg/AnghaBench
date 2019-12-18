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
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  iso_init (int) ; 
 int /*<<< orphan*/  mcs_hdr ; 
 int /*<<< orphan*/  s_push_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

STREAM
mcs_init(int length)
{
	STREAM s;

	s = iso_init(length + 8);
	s_push_layer(s, mcs_hdr, 8);

	return s;
}