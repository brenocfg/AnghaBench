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
struct bluray_priv_s {int /*<<< orphan*/  bd; scalar_t__ title_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  bd_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_free_title_info (scalar_t__) ; 

__attribute__((used)) static void destruct(struct bluray_priv_s *priv)
{
    if (priv->title_info)
        bd_free_title_info(priv->title_info);
    bd_close(priv->bd);
}