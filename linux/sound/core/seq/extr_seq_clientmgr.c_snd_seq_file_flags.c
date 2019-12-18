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
struct file {int f_mode; } ;

/* Variables and functions */
#define  FMODE_READ 129 
#define  FMODE_WRITE 128 
 unsigned short SNDRV_SEQ_LFLG_INPUT ; 
 unsigned short SNDRV_SEQ_LFLG_OPEN ; 
 unsigned short SNDRV_SEQ_LFLG_OUTPUT ; 

__attribute__((used)) static inline unsigned short snd_seq_file_flags(struct file *file)
{
        switch (file->f_mode & (FMODE_READ | FMODE_WRITE)) {
        case FMODE_WRITE:
                return SNDRV_SEQ_LFLG_OUTPUT;
        case FMODE_READ:
                return SNDRV_SEQ_LFLG_INPUT;
        default:
                return SNDRV_SEQ_LFLG_OPEN;
        }
}