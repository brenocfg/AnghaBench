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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE ; 
 int /*<<< orphan*/  fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

__attribute__((used)) static int read_till_nl(FILE *in)
{
#  define SIZE 4
    char buf[SIZE + 1];

    do {
        if (!fgets(buf, SIZE, in))
            return 0;
    } while (strchr(buf, '\n') == NULL);
    return 1;
}