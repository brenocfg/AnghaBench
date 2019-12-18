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
 char* LZ4_VERSION_STRING ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ validate (char const* const) ; 

int main(int argc, const char** argv)
{
    const char* const exeName = argv[0];
    const char* const tag = argv[1];
    if (argc!=2) {
        printf("incorrect usage : %s tag \n", exeName);
        return 2;
    }

    printf("Version : %s \n", LZ4_VERSION_STRING);
    printf("Tag     : %s \n", tag);

    if (validate(tag)) {
        printf("OK : tag is compatible with lz4 version \n");
        return 0;
    }

    printf("!! error : tag and versions are not compatible !! \n");
    return 1;
}