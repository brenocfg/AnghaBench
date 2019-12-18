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
typedef  int /*<<< orphan*/  libvlc_media_t ;

/* Variables and functions */
 int /*<<< orphan*/  libvlc ; 
 int /*<<< orphan*/ * libvlc_media_new_location_ (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * libvlc_media_new_path_ (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 

__attribute__((used)) static inline libvlc_media_t *create_media_from_file(const char *file)
{
	return (file && strstr(file, "://") != NULL)
		       ? libvlc_media_new_location_(libvlc, file)
		       : libvlc_media_new_path_(libvlc, file);
}