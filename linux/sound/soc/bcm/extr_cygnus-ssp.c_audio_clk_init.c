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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cygnus_audio {int /*<<< orphan*/ * audio_clk; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PROP_LEN_MAX ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int audio_clk_init(struct platform_device *pdev,
						struct cygnus_audio *cygaud)
{
	int i;
	char clk_name[PROP_LEN_MAX];

	for (i = 0; i < ARRAY_SIZE(cygaud->audio_clk); i++) {
		snprintf(clk_name, PROP_LEN_MAX, "ch%d_audio", i);

		cygaud->audio_clk[i] = devm_clk_get(&pdev->dev, clk_name);
		if (IS_ERR(cygaud->audio_clk[i]))
			return PTR_ERR(cygaud->audio_clk[i]);
	}

	return 0;
}