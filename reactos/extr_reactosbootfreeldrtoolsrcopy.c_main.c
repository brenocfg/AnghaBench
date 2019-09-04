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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TRANSFER_SIZE ; 
 char* convert_path (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fread (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char* argv[])
{
   char* path1;
   char* path2;
   FILE* in;
   FILE* out;
   char* buf;
   int n_in;
   int n_out;

   if (argc != 3)
     {
    fprintf(stderr, "Too many arguments\n");
    exit(1);
     }

   path1 = convert_path(argv[1]);
   path2 = convert_path(argv[2]);

   in = fopen(path1, "rb");
   if (in == NULL)
     {
    perror("Cannot open input file");
    exit(1);
     }



   out = fopen(path2, "wb");
   if (out == NULL)
     {
    perror("Cannot open output file");
    fclose(in);
    exit(1);
     }

   buf = malloc(TRANSFER_SIZE);

   while (!feof(in))
     {
    n_in = fread(buf, 1, TRANSFER_SIZE, in);
    n_out = fwrite(buf, 1, n_in, out);
    if (n_in != n_out)
      {
         perror("Failed to write to output file\n");
         free(buf);
         fclose(in);
         fclose(out);
         exit(1);
      }
     }
   exit(0);
}