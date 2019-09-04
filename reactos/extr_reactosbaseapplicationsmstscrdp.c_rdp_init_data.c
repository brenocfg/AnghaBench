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
 int /*<<< orphan*/  SEC_ENCRYPT ; 
 scalar_t__ g_encryption ; 
 int /*<<< orphan*/  rdp_hdr ; 
 int /*<<< orphan*/  s_push_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec_init (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static STREAM
rdp_init_data(int maxlen)
{
	STREAM s;

	s = sec_init(g_encryption ? SEC_ENCRYPT : 0, maxlen + 18);
	s_push_layer(s, rdp_hdr, 18);

	return s;
}