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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_INT_ENABLE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audio_data ; 
 int /*<<< orphan*/  audio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_count ; 

__attribute__((used)) static int goldfish_audio_release(struct inode *ip, struct file *fp)
{
	atomic_dec(&open_count);
	/* FIXME: surely this is wrong for the multi-opened case */
	audio_write(audio_data, AUDIO_INT_ENABLE, 0);
	return 0;
}