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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCP_SET ; 
 int dspio_scp (struct hda_codec*,int,int,int,int /*<<< orphan*/ ,void const*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dspio_set_param(struct hda_codec *codec, int mod_id,
			int src_id, int req, const void *data, unsigned int len)
{
	return dspio_scp(codec, mod_id, src_id, req, SCP_SET, data, len, NULL,
			NULL);
}