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
struct game_capture_config {int /*<<< orphan*/  executable; int /*<<< orphan*/  class; int /*<<< orphan*/  title; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct game_capture_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void free_config(struct game_capture_config *config)
{
	bfree(config->title);
	bfree(config->class);
	bfree(config->executable);
	memset(config, 0, sizeof(*config));
}