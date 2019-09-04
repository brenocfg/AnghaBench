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
struct bluray_priv_s {int /*<<< orphan*/  bd; } ;

/* Variables and functions */
 int bd_select_title (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) inline static int play_title(struct bluray_priv_s *priv, int title)
{
    return bd_select_title(priv->bd, title);
}