#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char tx_delay; unsigned char ppersist; unsigned char slottime; unsigned char tx_tail; int fulldup; } ;
struct hdlcdrv_state {TYPE_1__ ch_params; } ;

/* Variables and functions */
#define  PARAM_FULLDUP 132 
#define  PARAM_PERSIST 131 
#define  PARAM_SLOTTIME 130 
#define  PARAM_TXDELAY 129 
#define  PARAM_TXTAIL 128 

__attribute__((used)) static inline void do_kiss_params(struct hdlcdrv_state *s,
				  unsigned char *data, unsigned long len)
{

#ifdef KISS_VERBOSE
#define PKP(a,b) printk(KERN_INFO "hdlcdrv.c: channel params: " a "\n", b)
#else /* KISS_VERBOSE */	      
#define PKP(a,b) 
#endif /* KISS_VERBOSE */	      

	if (len < 2)
		return;
	switch(data[0]) {
	case PARAM_TXDELAY:
		s->ch_params.tx_delay = data[1];
		PKP("TX delay = %ums", 10 * s->ch_params.tx_delay);
		break;
	case PARAM_PERSIST:   
		s->ch_params.ppersist = data[1];
		PKP("p persistence = %u", s->ch_params.ppersist);
		break;
	case PARAM_SLOTTIME:  
		s->ch_params.slottime = data[1];
		PKP("slot time = %ums", s->ch_params.slottime);
		break;
	case PARAM_TXTAIL:    
		s->ch_params.tx_tail = data[1];
		PKP("TX tail = %ums", s->ch_params.tx_tail);
		break;
	case PARAM_FULLDUP:   
		s->ch_params.fulldup = !!data[1];
		PKP("%s duplex", s->ch_params.fulldup ? "full" : "half");
		break;
	default:
		break;
	}
#undef PKP
}