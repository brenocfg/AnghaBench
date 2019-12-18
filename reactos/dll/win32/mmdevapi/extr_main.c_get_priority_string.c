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
#define  Priority_Low 131 
#define  Priority_Neutral 130 
#define  Priority_Preferred 129 
#define  Priority_Unavailable 128 

__attribute__((used)) static const char *get_priority_string(int prio)
{
    switch(prio){
    case Priority_Unavailable:
        return "Unavailable";
    case Priority_Low:
        return "Low";
    case Priority_Neutral:
        return "Neutral";
    case Priority_Preferred:
        return "Preferred";
    }
    return "Invalid";
}