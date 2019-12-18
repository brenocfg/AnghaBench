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
struct snd_opl4 {int /*<<< orphan*/  res_pcm_port; int /*<<< orphan*/  res_fm_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_opl4*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_opl4_free_proc (struct snd_opl4*) ; 

__attribute__((used)) static void snd_opl4_free(struct snd_opl4 *opl4)
{
	snd_opl4_free_proc(opl4);
	release_and_free_resource(opl4->res_fm_port);
	release_and_free_resource(opl4->res_pcm_port);
	kfree(opl4);
}