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
struct key_preparsed_payload {scalar_t__ datalen; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int keyring_preparse(struct key_preparsed_payload *prep)
{
	return prep->datalen != 0 ? -EINVAL : 0;
}