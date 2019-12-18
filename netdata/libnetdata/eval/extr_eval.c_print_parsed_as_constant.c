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
typedef  int /*<<< orphan*/  calculated_number ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  CALCULATED_NUMBER_FORMAT ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  isinf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isnan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfz (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void print_parsed_as_constant(BUFFER *out, calculated_number n) {
    if(unlikely(isnan(n))) {
        buffer_strcat(out, "nan");
        return;
    }

    if(unlikely(isinf(n))) {
        buffer_strcat(out, "inf");
        return;
    }

    char b[100+1], *s;
    snprintfz(b, 100, CALCULATED_NUMBER_FORMAT, n);

    s = &b[strlen(b) - 1];
    while(s > b && *s == '0') {
        *s ='\0';
        s--;
    }

    if(s > b && *s == '.')
        *s = '\0';

    buffer_strcat(out, b);
}