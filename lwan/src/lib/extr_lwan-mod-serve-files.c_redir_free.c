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
struct redir_cache_data {int /*<<< orphan*/  redir_to; } ;
struct file_cache_entry {struct redir_cache_data redir_cache_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void redir_free(struct file_cache_entry *fce)
{
    struct redir_cache_data *rd = &fce->redir_cache_data;

    free(rd->redir_to);
}