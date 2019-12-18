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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {struct ca0132_spec* spec_init_verbs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ca0132_spec*) ; 
 int /*<<< orphan*/  zxr_dbpro_power_state_shutdown (struct hda_codec*) ; 

__attribute__((used)) static void dbpro_free(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;

	zxr_dbpro_power_state_shutdown(codec);

	kfree(spec->spec_init_verbs);
	kfree(codec->spec);
}