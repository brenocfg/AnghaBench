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
typedef  int /*<<< orphan*/  obs_encoder_t ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 double obs_data_get_double (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_encoder_get_settings (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline double encoder_bitrate(obs_encoder_t *encoder)
{
	obs_data_t *settings = obs_encoder_get_settings(encoder);
	double bitrate = obs_data_get_double(settings, "bitrate");

	obs_data_release(settings);
	return bitrate;
}