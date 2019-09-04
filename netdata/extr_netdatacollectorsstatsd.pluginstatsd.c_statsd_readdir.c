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

/* Variables and functions */
 int /*<<< orphan*/  recursive_config_double_dir_load (char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statsd_file_callback ; 

__attribute__((used)) static inline void statsd_readdir(const char *user_path, const char *stock_path, const char *subpath) {
    recursive_config_double_dir_load(user_path, stock_path, subpath, statsd_file_callback, NULL, 0);
}