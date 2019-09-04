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
typedef  char* LPSTR ;

/* Variables and functions */

__attribute__((used)) static void convert_nfs4name_2_user_domain(LPSTR nfs4name, 
                                           LPSTR *domain)
{
    LPSTR p = nfs4name;
    for(; p[0] != '\0'; p++) {
        if (p[0] == '@') { 
            p[0] = '\0';
            *domain = &p[1];
            break;
        }
    }
}