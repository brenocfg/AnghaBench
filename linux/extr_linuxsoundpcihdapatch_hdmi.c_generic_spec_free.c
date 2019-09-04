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
struct hdmi_spec {int dummy; } ;
struct hda_codec {int dp_mst; struct hdmi_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  hdmi_array_free (struct hdmi_spec*) ; 
 int /*<<< orphan*/  kfree (struct hdmi_spec*) ; 

__attribute__((used)) static void generic_spec_free(struct hda_codec *codec)
{
	struct hdmi_spec *spec = codec->spec;

	if (spec) {
		hdmi_array_free(spec);
		kfree(spec);
		codec->spec = NULL;
	}
	codec->dp_mst = false;
}