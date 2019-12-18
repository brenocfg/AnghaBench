#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  file ;
struct TYPE_3__ {int /*<<< orphan*/  pathFileOffset; } ;
typedef  TYPE_1__ cache_img_t ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char *get_lib_name(RBuffer *cache_buf, cache_img_t *img) {
	char file[256];
	char *lib_name = file;
	if (r_buf_read_at (cache_buf, img->pathFileOffset, (ut8*) &file, sizeof (file)) == sizeof (file)) {
		file[255] = 0;
		/*char * last_slash = strrchr (file, '/');
		if (last_slash && *last_slash) {
			lib_name = last_slash + 1;
		}*/
		return strdup (lib_name);
	}
	return strdup ("FAIL");
}