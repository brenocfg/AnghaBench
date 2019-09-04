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
#define  MP_FOURCC_I420 133 
#define  MP_FOURCC_JPEG 132 
#define  MP_FOURCC_MJPEG 131 
#define  MP_FOURCC_UYVY 130 
#define  MP_FOURCC_YUY2 129 
#define  MP_FOURCC_YV12 128 
 int /*<<< orphan*/  memset (char*,int,int) ; 

__attribute__((used)) static inline void fill_blank_frame(char* buffer,int len,int fmt){
    int i;
    // RGB(0,0,255) <-> YVU(41,110,240)

    switch(fmt){
    case MP_FOURCC_YV12:
        memset(buffer, 41,4*len/6);       //Y
        memset(buffer+4*len/6, 110,len/6);//V
        memset(buffer+5*len/6, 240,len/6);//U
        break;
    case MP_FOURCC_I420:
        memset(buffer, 41,4*len/6);       //Y
        memset(buffer+4*len/6, 240,len/6);//U
        memset(buffer+5*len/6, 110,len/6);//V
        break;
    case MP_FOURCC_UYVY:
        for(i=0;i<len;i+=4){
            buffer[i]=0xFF;
            buffer[i+1]=0;
            buffer[i+2]=0;
            buffer[i+3]=0;
        }
        break;
    case MP_FOURCC_YUY2:
        for(i=0;i<len;i+=4){
            buffer[i]=0;
            buffer[i+1]=0xFF;
            buffer[i+2]=0;
            buffer[i+3]=0;
        }
        break;
    case MP_FOURCC_MJPEG:
    case MP_FOURCC_JPEG:
        /*
        This is compressed format. I don't know yet how to fill such frame with blue color.
        Keeping frame unchanged.
        */
        break;
    default:
        memset(buffer,0xC0,len);
    }
}