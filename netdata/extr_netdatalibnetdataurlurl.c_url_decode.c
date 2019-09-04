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
 char* mallocz (size_t) ; 
 int strlen (char*) ; 
 char* url_decode_r (char*,char*,size_t) ; 

char *url_decode(char *str) {
    size_t size = strlen(str) + 1;

    char *buf = mallocz(size);
    return url_decode_r(buf, str, size);
}