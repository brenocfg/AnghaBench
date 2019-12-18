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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LLVMFuzzerTestOneInput (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
  int ii;
  for(ii = 1; ii < argc; ii++)
  {
    FILE *infile;
    printf("[%s] ", argv[ii]);

    /* Try and open the file. */
    infile = fopen(argv[ii], "rb");
    if(infile)
    {
      uint8_t *buffer = NULL;
      size_t buffer_len;

      printf("Opened.. ");

      /* Get the length of the file. */
      fseek(infile, 0L, SEEK_END);
      buffer_len = ftell(infile);

      /* Reset the file indicator to the beginning of the file. */
      fseek(infile, 0L, SEEK_SET);

      /* Allocate a buffer for the file contents. */
      buffer = (uint8_t *)calloc(buffer_len, sizeof(uint8_t));
      if(buffer)
      {
        /* Read all the text from the file into the buffer. */
        fread(buffer, sizeof(uint8_t), buffer_len, infile);
        printf("Read %zu bytes, fuzzing.. ", buffer_len);

        /* Call the fuzzer with the data. */
        LLVMFuzzerTestOneInput(buffer, buffer_len);

        printf("complete !!");

        /* Free the buffer as it's no longer needed. */
        free(buffer);
        buffer = NULL;
      }
      else
      {
        fprintf(stderr,
                "[%s] Failed to allocate %zu bytes \n",
                argv[ii],
                buffer_len);
      }

      /* Close the file as it's no longer needed. */
      fclose(infile);
      infile = NULL;
    }
    else
    {
      /* Failed to open the file. Maybe wrong name or wrong permissions? */
      fprintf(stderr, "[%s] Open failed. \n", argv[ii]);
    }

    printf("\n");
  }
}