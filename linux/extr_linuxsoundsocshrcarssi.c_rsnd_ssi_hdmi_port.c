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
struct rsnd_ssi {int dummy; } ;
struct rsnd_mod {int dummy; } ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSND_SSI_HDMI0 ; 
 int /*<<< orphan*/  RSND_SSI_HDMI1 ; 
 int RSND_SSI_HDMI_PORT0 ; 
 int RSND_SSI_HDMI_PORT1 ; 
 scalar_t__ rsnd_flags_has (struct rsnd_ssi*,int /*<<< orphan*/ ) ; 
 struct rsnd_mod* rsnd_io_to_mod_ssi (struct rsnd_dai_stream*) ; 
 struct rsnd_ssi* rsnd_mod_to_ssi (struct rsnd_mod*) ; 

int rsnd_ssi_hdmi_port(struct rsnd_dai_stream *io)
{
	struct rsnd_mod *mod = rsnd_io_to_mod_ssi(io);
	struct rsnd_ssi *ssi = rsnd_mod_to_ssi(mod);

	if (rsnd_flags_has(ssi, RSND_SSI_HDMI0))
		return RSND_SSI_HDMI_PORT0;

	if (rsnd_flags_has(ssi, RSND_SSI_HDMI1))
		return RSND_SSI_HDMI_PORT1;

	return 0;
}