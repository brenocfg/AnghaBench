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

__attribute__((used)) static const char *
response_code(unsigned code)
{
#define CODE(x,y) (((x)<<5) | (y))
    switch (code) {
        case CODE(2,0): return "Okay";
        case CODE(2,1): return "Created";
        case CODE(2,2): return "Deleted";
        case CODE(2,3): return "Valid";
        case CODE(2,4): return "Changed";
        case CODE(2,5): return "Content";
        
        case CODE(4,0): return "Bad Request";
        case CODE(4,1): return "Unauthorized";
        case CODE(4,2): return "Bad Option";
        case CODE(4,3): return "Forbidden";
        case CODE(4,4): return "Not Found";
        case CODE(4,5): return "Method Not Allowed";
        case CODE(4,6): return "Not Acceptable";
        case CODE(4,12): return "Precondition Failed";
        case CODE(4,13): return "Request Too Large";
        case CODE(4,15): return "Unsupported Content-Format";
            
        case CODE(5,0): return "Internal Server Error";
        case CODE(5,1): return "Not Implemented";
        case CODE(5,2): return "Bad Gateway";
        case CODE(5,3): return "Service Unavailable";
        case CODE(5,4): return "Gateway Timeout";
        case CODE(5,5): return "Proxying Not Supported";
    }
    
    switch (code>>5) {
        case 2: return "Okay";
        case 4: return "Error";
        default: return "PARSE_ERR";
    }
}