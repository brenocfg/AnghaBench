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
struct alsa_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ _alsa_open (struct alsa_data*) ; 
 int /*<<< orphan*/  _alsa_start_reopen (struct alsa_data*) ; 
 int /*<<< orphan*/  _alsa_stop_reopen (struct alsa_data*) ; 

bool _alsa_try_open(struct alsa_data *data)
{
	_alsa_stop_reopen(data);

	if (_alsa_open(data))
		return true;

	_alsa_start_reopen(data);

	return false;
}