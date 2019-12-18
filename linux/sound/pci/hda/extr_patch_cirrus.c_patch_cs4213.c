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
struct hda_codec {int /*<<< orphan*/  patch_ops; } ;
struct cs_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4213_VENDOR_NID ; 
 int ENOMEM ; 
 int cs421x_parse_auto_config (struct hda_codec*) ; 
 int /*<<< orphan*/  cs421x_patch_ops ; 
 struct cs_spec* cs_alloc_spec (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_free (struct hda_codec*) ; 

__attribute__((used)) static int patch_cs4213(struct hda_codec *codec)
{
	struct cs_spec *spec;
	int err;

	spec = cs_alloc_spec(codec, CS4213_VENDOR_NID);
	if (!spec)
		return -ENOMEM;

	codec->patch_ops = cs421x_patch_ops;

	err = cs421x_parse_auto_config(codec);
	if (err < 0)
		goto error;

	return 0;

 error:
	cs_free(codec);
	return err;
}