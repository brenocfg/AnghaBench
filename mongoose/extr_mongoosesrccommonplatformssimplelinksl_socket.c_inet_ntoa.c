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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  a ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ inet_ntop (int /*<<< orphan*/ ,struct in_addr*,char*,int) ; 

char *inet_ntoa(struct in_addr n) {
  static char a[16];
  return (char *) inet_ntop(AF_INET, &n, a, sizeof(a));
}