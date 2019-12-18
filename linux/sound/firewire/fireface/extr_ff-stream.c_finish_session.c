#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_ff {TYPE_2__* spec; } ;
struct TYPE_4__ {TYPE_1__* protocol; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* switch_fetching_mode ) (struct snd_ff*,int) ;int /*<<< orphan*/  (* finish_session ) (struct snd_ff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct snd_ff*) ; 
 int /*<<< orphan*/  stub2 (struct snd_ff*,int) ; 

__attribute__((used)) static inline void finish_session(struct snd_ff *ff)
{
	ff->spec->protocol->finish_session(ff);
	ff->spec->protocol->switch_fetching_mode(ff, false);
}