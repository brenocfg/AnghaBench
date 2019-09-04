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
 unsigned char BIT0 ; 
 unsigned char BIT1 ; 
 unsigned char BIT2 ; 
 unsigned char BIT4 ; 
 unsigned char BIT5 ; 
 unsigned char BIT6 ; 
 unsigned char BIT7 ; 
 unsigned short NVMEM_RM_FILEID ; 
 unsigned char nvmem_read (int,int,int,unsigned char*) ; 

__attribute__((used)) static unsigned char  __attribute__ ((unused))
fat_read_content(unsigned char *is_allocated, unsigned char *is_valid,
        unsigned char *write_protected, unsigned short *file_address, unsigned short *file_length)
{
    unsigned short  index;
    unsigned char   ucStatus;
    unsigned char   fatTable[48];
    unsigned char*  fatTablePtr = fatTable;

    //
    // Read in 6 parts to work with tiny driver
    //
    for (index = 0; index < 6; index++)
    {
        ucStatus = nvmem_read(16, 8, 4 + 8*index, fatTablePtr); 
        fatTablePtr += 8;
    }
	
    fatTablePtr = fatTable;
	
    for (index = 0; index <= NVMEM_RM_FILEID; index++)
    {
        *is_allocated++ = (*fatTablePtr) & BIT0;
        *is_valid++ = ((*fatTablePtr) & BIT1) >> 1;
        *write_protected++ = ((*fatTablePtr) & BIT2) >> 2;
        *file_address++ = ((*(fatTablePtr+1)<<8) | (*fatTablePtr)) & (BIT4|BIT5|BIT6|BIT7);
        *file_length++ = ((*(fatTablePtr+3)<<8) | (*(fatTablePtr+2))) & (BIT4|BIT5|BIT6|BIT7);
        
        //
        // Move to next file ID
        //
        fatTablePtr += 4;  
    }
    
    return ucStatus;
}