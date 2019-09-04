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
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int FILE_ATTRIBUTE_REPARSE_POINT ; 
 int INVALID_FILE_ATTRIBUTES ; 
 int MP_S_IFDIR ; 
 int MP_S_IFREG ; 

int dttoif(int d_type) {
    if (d_type == INVALID_FILE_ATTRIBUTES) {
        return 0;
    }
    // Could be a couple of things (symlink, junction, ...) and non-trivial to
    // figure out so just report it as unknown. Should we ever want this then
    // the proper code can be found in msvc's std::filesystem implementation.
    if (d_type & FILE_ATTRIBUTE_REPARSE_POINT) {
        return 0;
    }
    return (d_type & FILE_ATTRIBUTE_DIRECTORY) ? MP_S_IFDIR : MP_S_IFREG;
}