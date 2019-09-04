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
struct nid_path {int depth; int active; int pin_fixed; int stream_enabled; int /*<<< orphan*/ * path; } ;
struct hda_gen_spec {int /*<<< orphan*/  paths; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  memset (struct nid_path*,int /*<<< orphan*/ ,int) ; 
 struct nid_path* snd_array_new (int /*<<< orphan*/ *) ; 

int snd_hda_gen_fix_pin_power(struct hda_codec *codec, hda_nid_t pin)
{
	struct hda_gen_spec *spec = codec->spec;
	struct nid_path *path;

	path = snd_array_new(&spec->paths);
	if (!path)
		return -ENOMEM;
	memset(path, 0, sizeof(*path));
	path->depth = 1;
	path->path[0] = pin;
	path->active = true;
	path->pin_fixed = true;
	path->stream_enabled = true;
	return 0;
}