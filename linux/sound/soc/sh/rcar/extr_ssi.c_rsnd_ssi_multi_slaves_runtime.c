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
typedef  int /*<<< orphan*/  u32 ;
struct rsnd_dai_stream {int dummy; } ;

/* Variables and functions */
 scalar_t__ rsnd_runtime_is_multi_ssi (struct rsnd_dai_stream*) ; 
 int /*<<< orphan*/  rsnd_ssi_multi_slaves (struct rsnd_dai_stream*) ; 

u32 rsnd_ssi_multi_slaves_runtime(struct rsnd_dai_stream *io)
{
	if (rsnd_runtime_is_multi_ssi(io))
		return rsnd_ssi_multi_slaves(io);

	return 0;
}