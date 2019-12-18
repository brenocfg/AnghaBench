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
 int atoi (char*) ; 
 char* iface ; 
 int net__addr_v4_add (char*,int) ; 
 int net__addr_v6_add (char*,int) ; 
 int net__iface_mtu_set (int) ; 
 int net__iface_up (int) ; 
 int net__route_v4_add (char*,int,int /*<<< orphan*/ ) ; 
 int net__route_v4_add_gw (char*,int,char*,int /*<<< orphan*/ ) ; 
 int net__route_v6_add (char*,int,int) ; 
 int net__route_v6_add_gw (char*,int,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[])
{
    int test;

    if (argc < 2)
    {
        usage(argv[0]);
        return -1;
    }

    /* the t_net script can use this command to perform a dry-run test */
    if (strcmp(argv[1], "test") == 0)
    {
        return 0;
    }

    if (argc > 3)
    {
        iface = argv[2];
    }

    test = atoi(argv[1]);
    switch (test)
    {
        case 0:
            return net__iface_up(true);
        case 1:
            return net__iface_mtu_set(1281);
        case 2:
            return net__addr_v4_add("10.255.255.1", 24);
        case 3:
            return net__addr_v6_add("2001::1", 64);
        case 4:
            return net__route_v4_add("11.11.11.0", 24, 0);
        case 5:
            return net__route_v4_add_gw("11.11.12.0", 24, "10.255.255.2", 0);
        case 6:
            return net__route_v6_add("2001:babe:cafe:babe::", 64, 600);
        case 7:
            return net__route_v6_add_gw("2001:cafe:babe::", 48, "2001::2", 600);
        default:
            printf("invalid test: %d\n", test);
            break;
    }

    usage(argv[0]);
    return -1;
}