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
#define  AFMT_A_LAW 135 
#define  AFMT_MU_LAW 134 
#define  AFMT_S16_BE 133 
#define  AFMT_S16_LE 132 
#define  AFMT_S8 131 
#define  AFMT_U16_BE 130 
#define  AFMT_U16_LE 129 
#define  AFMT_U8 128 

__attribute__((used)) static char *get_afmt_string(int afmt)
{
        switch(afmt) {
            case AFMT_MU_LAW:
                return "mu-law";
                break;
            case AFMT_A_LAW:
                return "A-law";
                break;
            case AFMT_U8:
                return "unsigned 8 bit";
                break;
            case AFMT_S8:
                return "signed 8 bit";
                break;
            case AFMT_S16_BE:
                return "signed 16 bit BE";
                break;
            case AFMT_U16_BE:
                return "unsigned 16 bit BE";
                break;
            case AFMT_S16_LE:
                return "signed 16 bit LE";
                break;
            case AFMT_U16_LE:
                return "unsigned 16 bit LE";
                break;
	    case 0:
		return "format not set" ;
		break ;
            default:
                break ;
        }
        return "ERROR: Unsupported AFMT_XXXX code" ;
}