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
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int r_io_zip_check_uri (char const*) ; 
 int r_io_zip_check_uri_many (char const*) ; 

__attribute__((used)) static bool r_io_zip_plugin_open(RIO *io, const char *file, bool many) {
	if (io && file) {
		if (many) {
			return r_io_zip_check_uri_many (file);
		}
		return r_io_zip_check_uri (file);
	}
	return false;
}