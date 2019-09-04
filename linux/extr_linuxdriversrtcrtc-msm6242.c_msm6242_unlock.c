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
struct msm6242_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSM6242_CD ; 
 int /*<<< orphan*/  MSM6242_CD_HOLD ; 
 int /*<<< orphan*/  msm6242_clear (struct msm6242_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm6242_unlock(struct msm6242_priv *priv)
{
	msm6242_clear(priv, MSM6242_CD_HOLD, MSM6242_CD);
}