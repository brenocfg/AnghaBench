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
struct Masscan {double max_rate; scalar_t__ echo; } ;

/* Variables and functions */
 int CONF_ERR ; 
 int CONF_OK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int SET_rate(struct Masscan *masscan, const char *name, const char *value)
{
    double rate = 0.0;
    double point = 10.0;
    unsigned i;
    
    if (masscan->echo) {
        fprintf(masscan->echo, "rate = %-10.2f\n", masscan->max_rate);
        return 0;
    }
    
    for (i=0; value[i] && value[i] != '.'; i++) {
        char c = value[i];
        if (c < '0' || '9' < c) {
            fprintf(stderr, "CONF: non-digit in rate spec: %s=%s\n", name, value);
            return CONF_ERR;
        }
        rate = rate * 10.0 + (c - '0');
    }
    
    if (value[i] == '.') {
        i++;
        while (value[i]) {
            char c = value[i];
            if (c < '0' || '9' < c) {
                fprintf(stderr, "CONF: non-digit in rate spec: %s=%s\n",
                        name, value);
                return CONF_ERR;
            }
            rate += (c - '0')/point;
            point /= 10.0;
            value++;
        }
    }
    
    masscan->max_rate = rate;
    return CONF_OK;
}