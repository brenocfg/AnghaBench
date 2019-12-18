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
typedef  int ut32 ;

/* Variables and functions */
 char* hex_str ; 
 char* strdup (char*) ; 

char *get_hex_str(ut32 hex_num) {
    char aux[3];

    aux[2] = '\0';
    aux[1] = hex_str[hex_num & 0xF];
    aux[0] = hex_str[(hex_num >> 4) & 0xF];

    return strdup(aux);
}