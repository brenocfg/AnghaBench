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
struct si3054_spec {int dummy; } ;
struct hda_codec {int /*<<< orphan*/  patch_ops; struct si3054_spec* spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct si3054_spec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si3054_patch_ops ; 

__attribute__((used)) static int patch_si3054(struct hda_codec *codec)
{
	struct si3054_spec *spec = kzalloc(sizeof(*spec), GFP_KERNEL);
	if (spec == NULL)
		return -ENOMEM;
	codec->spec = spec;
	codec->patch_ops = si3054_patch_ops;
	return 0;
}