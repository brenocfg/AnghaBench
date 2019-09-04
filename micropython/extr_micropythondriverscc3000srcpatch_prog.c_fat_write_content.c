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
typedef  int /*<<< orphan*/  fatTable ;

/* Variables and functions */
 unsigned char BIT0 ; 
 unsigned short NVMEM_RM_FILEID ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 unsigned char nvmem_write (int,int,int,unsigned char*) ; 

__attribute__((used)) static unsigned char fat_write_content(unsigned short const *file_address,
                                unsigned short const *file_length)
{
    unsigned short  index = 0;
    unsigned char   ucStatus;
    unsigned char   fatTable[48];
    unsigned char*  fatTablePtr = fatTable;

    //
    // First, write the magic number.
    //
    ucStatus = nvmem_write(16, 2, 0, (unsigned char*)"LS"); 
	
    for (; index <= NVMEM_RM_FILEID; index++)
    {
        //
        // Write address low char and mark as allocated.
        //
        *fatTablePtr++ = (unsigned char)(file_address[index] & 0xff) | BIT0;
	
        //	
        // Write address high char.
        //
        *fatTablePtr++ = (unsigned char)((file_address[index]>>8) & 0xff);
		
        //
        // Write length low char.
        //
        *fatTablePtr++ = (unsigned char)(file_length[index] & 0xff);
		
        //
        // Write length high char.
        //
        *fatTablePtr++ = (unsigned char)((file_length[index]>>8) & 0xff);		
    }
	
    //
    // Second, write the FAT.
    // Write in two parts to work with tiny driver.
    //
    ucStatus = nvmem_write(16, 24, 4, fatTable); 
    ucStatus = nvmem_write(16, 24, 24+4, &fatTable[24]); 
	
    //
    // Third, we want to erase any user files.
    //
    memset(fatTable, 0, sizeof(fatTable));
    ucStatus = nvmem_write(16, 16, 52, fatTable); 
	
    return ucStatus;
}